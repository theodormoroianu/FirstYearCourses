/**
 * This code takes care of creating the "signup" menu, and processing the request
 */



/// HTML CODE NEEDED TO RENDER THE PAGE -----------------------------------------------------------------------------------------

SIGNUP_html_code =
`<div id="create-user">
    <header class='title'>
        <h1>New User</h1>
    </header>

    <section id="main">
        <form action='#' onsubmit="SIGNUP_VerifyData();return false">
            <label for="name"><b>Name</b></label>
            <input type="text" placeholder="Enter Your Name" name="name" id="name" required>
            <label for="username"><b>Username</b></label>
            <input type="text" placeholder="Enter Your Prefered Username" name="username" id="username" required>
            <label for="password"><b>Password</b></label>
            <input type="password" placeholder="Enter Your Password" name="password" id="password" required>
            <input type="password" placeholder="Enter Your Password Again" name="password" id="password_verification" required>
            <div id="warning">
            </div>
            <div id="positive-warning">
            </div>
            <button type="submit">Create Account</button>
            <button onclick="SIGNUP_Cancel()">Cancel</button>
        </form>
    </section>
</div>`;



/// SIDE FUNCTIONS NEEDED -------------------------------------------------------------------------------------------------------

var SIGNUP_callback = null;

var SIGNUP_Cancel = function() {
    SIGNUP_callback();
}

var SIGNUP_ValidUserName = str => {
    if ((typeof str) !== "string")
        return false;
    if (str.length == 0 || str.length > 100 ||
      str.match(/^[0-9a-z\._]*$/ig) === null)
        return false;
    return true;    
};



/// FUNCTION THAT VERIFIES IF THE SERVER ACCEPTED THE REQUEST -------------------------------------------------------------------

/// receives the message back from the server
var SIGNUP_checker = function(obj) {
    if (obj.authentification.authentificated) {
        document.getElementById("warning").innerHTML = "";
        document.getElementById("positive-warning").innerHTML =
            "<p>Account Sucessfully Created. Redirecting to Login Page...</p>";
        setTimeout(SIGNUP_callback, 1500);
    }
    else
        document.getElementById("warning").innerHTML = "<p>" + obj.authentification.message + "</p>";
}



/// FUNCTION THAT VERIFIES IF THE DATA IS CORECT --------------------------------------------------------------------------------

/// if the form is submited, this function checks it and ultimatly makes a server request
var SIGNUP_VerifyData = function() {
    var user = document.getElementById("username").value;
    if (!SIGNUP_ValidUserName(user)) {
        document.getElementById("warning").innerHTML = "<p>Please enter a valid username</p>";
        return;
    }
    var password = document.getElementById("password").value;
    var password_verif = document.getElementById("password_verification").value;

    if (password !== password_verif) {
        document.getElementById("warning").innerHTML = "<p>The two passwords don't match!</p>";
        return;
    }

    if (password.length < 6) {
        document.getElementById("warning").innerHTML = "<p>Please enter a longer password</p>";
        return;
    }
    SYNC_CreateUser(user, name, password, SIGNUP_checker);
}



/// FUNCTION THAT RENDERS THE WINDOW --------------------------------------------------------------------------------------------

/// it creates the html file
var SIGNUP_Signup = function(callback) {
    SIGNUP_callback = callback;
    var wrapper = document.getElementById('wrapper');
    wrapper.innerHTML = SIGNUP_html_code;
}