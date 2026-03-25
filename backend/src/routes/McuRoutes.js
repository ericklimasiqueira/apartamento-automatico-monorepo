const express = require('express')
const router = express.Router()


const McuController = require('../controller/McuController')

//GET DOS ESTADOS DAS LUZES
router.get('/status-lights', McuController.getStateLights)

//PATCH PARA DESLIGAR OU LIGAR LUZES
router.patch('/:id/lights/toggle-active', McuController.patchStateLights)

//CONEXÃO AO APP.JS
module.exports = router

