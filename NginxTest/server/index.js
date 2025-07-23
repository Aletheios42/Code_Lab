const express = require("express")

const app = express()

let counter = 0;
app.get("/", (req, res) => {
    res.send("I am an endpoint, and i have been visited " + counter++ + " times")
})


app.listen(7777, ()=> {

    console.log("listening on port 7777")
})
