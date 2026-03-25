class McuServices {
    static async getStateLights() {
        const mockData = [
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
    
        return mockData;
    }
}

module.exports = McuServices;