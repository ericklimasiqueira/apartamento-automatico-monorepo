const express = require('express')
require('dotenv').config();
const app = express()
const port = 3000

const mcuRoutes = require('./routes/McuRoutes')

const authRoutes = require('./routes/authRoutes')

app.use(express.json())

//saúde do servidor

app.get('/health', (req, res) => {
    res.json({ status: 'ok', timestamp: new Date() });

    console.log('Servidor OK')
});


//Rota do server ao mcu

app.use('/mcu', mcuRoutes)

//Rota do server ao auth
app.use('/auth', authRoutes)

app.listen(port, () => {
  console.log(`Servidor rodando em http://localhost:${port}`);
});


module.exports = app
