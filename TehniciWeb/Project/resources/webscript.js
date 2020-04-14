var State = {
    date: "Now",
    data: ""
};

function SyncContent(){
    // Selecting the input element and get its value 
    var inputVal = document.getElementById("textbox").value;
    
    State.data = inputVal;

    var xhttp = new XMLHttpRequest();

    xhttp.open("POST", "api/sync_content", true);
    xhttp.setRequestHeader("Content-type", "application/json");
    xhttp.send(JSON.stringify(State));

    setTimeout(SyncContent, 1000);
}

function RequestContent(){
    var inputVal = document.getElementById("textbox").value;
    
    var xhttp = new XMLHttpRequest();

    xhttp.open("POST", "api/request_content", true);
    xhttp.setRequestHeader("Content-type", "application/json");
    xhttp.onreadystatechange = function() {
        console.log(this.response);
        State.data = JSON.parse(this.response).data;
    };
    xhttp.send('{ "user": "Marco", "password": "Polo" }');

}

RequestContent();
SyncContent();

