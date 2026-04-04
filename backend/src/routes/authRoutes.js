const express = require('express')
const router = express.Router()

const AuthController = require('../controller/AuthController')

//cadastrar novos user dentro do sistema
router.post('/register', AuthController.postRegisterUser)


//login de user dentro do sistema
router.post('/login', AuthController.postLoginUser)

//logout de user dentro do sistema

router.post('/logout', AuthController.postLogoutUser)

module.exports = router