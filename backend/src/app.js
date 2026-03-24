const express = require('express')
const app = express()
const port = 3000

const mcuRoutes = require('./routes/McuRoutes')

//saúde do servidor

app.get('/health', (req, res) => {
    res.json({ status: 'ok', timestamp: new Date() });

    console.log('Servidor OK')
});


//logica do server ao mcu

app.use('/mcu', mcuRoutes)

app.listen(port, () => {
  console.log(`Servidor rodando em http://localhost:${port}`);
});


module.exports = app
