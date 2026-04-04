const { json } = require("express");

class McuServices {

    static mockData = [
        {
            id: 1,
            lightName: "Luz do Quarto",
            isOn: true
        },

        {
            id: 2,
            lightName: "Luz da Sala",
            isOn: false
        },

        {
            id: 3,
            lightName: "Luz da Cozinha",
            isOn: true
        }
    ]

    static async getStateLights() {
        return this.mockData;
    }

    static async patchStateLights(id) {
        const light = this.mockData.find(l => l.id === id)

        if (!light) {
            throw new Error('Luz não encontrada')
        }

        // toggle correto
        light.isOn = !light.isOn

        return light
    }

}

module.exports = McuServices;