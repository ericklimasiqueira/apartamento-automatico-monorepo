'use strict';

const McuService = require('../services/McuServices')

const McuController = {


    getStateLights: async (req, res) => {
        try {
            const data = await McuService.getStateLights();

            return res.status(200).json(data)
        } catch (err) {
            return res.status(500).json({
                error: err.message
            })
        }
    },

    patchStateLights: async (req, res) => {
        res.json({mensage: "CONTROLLER FUNCIONANDO PORRA!"})
    },

}

module.exports = McuController;