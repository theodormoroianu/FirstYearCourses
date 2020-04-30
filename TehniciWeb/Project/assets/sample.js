
// fetch the dogs list
// doesnt work as we aren't able to send a json with a get request
function getDogs() {
    const getObject = {
        name: "get object",
        attrib: "random stuff"
    }
    // get dog
    fetch('dogs').then(function (response) {
            // Trasform server response to get the dogs
            response.json().then(function (dogs) {
                console.log("Received from get:");
                console.log(dogs);
            });
        });
};


// op can be put post delete
function opDog(type) {
    // creat post object
    const postObject = {
        name: "post object",
        attrib: "random stuff"
    }
    // post dog
    fetch('dogs', {
        method: type,
        headers: {
            "Content-type": "application/json"
        },
        body: JSON.stringify(postObject)
    }).then(function (response) {
        console.log("Sent post stuff");
        response.json().then(function (dogs) {
            console.log("Received from get:");
            console.log(dogs);
        });
    });
}

// op can be put post delete
var op2Dog = async () => {
    // creat post object
    const postObject = {
        name: "post object",
        attrib: "random stuff"
    }
    // post dog
    var obj = await fetch('dogs', {
        method: "POST",
        headers: {
            "Content-type": "application/json"
        },
        body: JSON.stringify(postObject)
    });
    var objj = await obj.json();
    console.log(objj);
    return objj;
}
