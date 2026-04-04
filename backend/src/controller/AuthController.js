'use strict';
const bcrypt = require('bcryptjs');
const jwt    = require('jsonwebtoken');
const db     = require('../database/db');

const AuthController = {
    postRegisterUser: async (req, res) => {
        const { name, email, password } = req.body;

        if (!name || !email || !password)
            return res.status(400).json({ error: 'Campos obrigatórios faltando' });

        const userExists = db.prepare('SELECT id FROM users WHERE email = ?').get(email);

        if (userExists)
            return res.status(409).json({ error: 'Email já cadastrado' });

        const hashedPassword = await bcrypt.hash(password, 10);

        const result = db
            .prepare('INSERT INTO users (name, email, password) VALUES (?, ?, ?)')
            .run(name, email, hashedPassword);

        return res.status(201).json({ message: 'Usuário criado', id: result.lastInsertRowid });
    },

    postLoginUser: async (req, res) => {
        const { email, password } = req.body;

        const user = db.prepare('SELECT * FROM users WHERE email = ?').get(email);

        if (!user)
            return res.status(401).json({ error: 'Credenciais inválidas' });

        const passwordMatch = await bcrypt.compare(password, user.password);

        if (!passwordMatch)
            return res.status(401).json({ error: 'Credenciais inválidas' });

        const accessToken = jwt.sign(
            { id: user.id, email: user.email },
            process.env.JWT_SECRET,
            { expiresIn: process.env.JWT_EXPIRES_IN }
        );

        const refreshToken = jwt.sign(
            { id: user.id },
            process.env.JWT_SECRET,
            { expiresIn: '7d' }
        );

        db.prepare('INSERT INTO refresh_tokens (user_id, token) VALUES (?, ?)').run(user.id, refreshToken);

        return res.json({ accessToken, refreshToken });
    },

    postLogoutUser: async (req, res) => {
        const { refreshToken } = req.body;
        db.prepare('DELETE FROM refresh_tokens WHERE token = ?').run(refreshToken);
        return res.json({ message: 'Logout realizado' });
    }
};

module.exports = AuthController;