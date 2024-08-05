const express = require('express');
const addon = require('./build/Release/encrypt');

const app = express();
app.use(express.json());

app.post('/api/encrypt', (req, res) => {
    const { password } = req.body;
    if (!password) {
        return res.status(400).json({ error: 'Password is required' });
    }
    try {
        const encryptedPassword = addon.encrypt(password);
        res.json({ encrypted: encryptedPassword });
    } catch (err) {
        res.status(500).json({ error: 'Encryption failed' });
    }
});

const port = 3000;
app.listen(port, () => {
    console.log(`Server running on http://localhost:${port}`);
});