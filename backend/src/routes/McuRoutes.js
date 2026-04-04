const express = require('express')
const router = express.Router()

const authMiddleware = require('../middleware/auth');
const McuController = require('../controller/McuController')

//GET DOS ESTADOS DAS LUZES
router.get('/status-lights', authMiddleware, McuController.getStateLights)

//PATCH PARA DESLIGAR OU LIGAR LUZES
router.patch('/lights/toggle-active', authMiddleware, McuController.patchStateLights)

//CONEXÃO AO APP.JS
module.exports = router

