/**
 * This script takes care of the login screen and returns a JSON with the user data (using the sync.js file)
 */



/// HTML CODE NEEDED TO RENDER THE PAGE -----------------------------------------------------------------------------------------

LOGIN_html_code =
`<div id="login">
    <header class='title'>
        <h1>Login Page</h1>
    </header>

    <section id="main">
        <form action='#' onsubmit="LOGIN_VerifyData();return false">
            <label for="username"><b>Username</b></label>
            <input type="text" placeholder="Enter Username" name="username" id="username" required>
            <label for="password"><b>Password</b></label>
            <input type="password" placeholder="Enter Password" name="password" id="password" required>
            <div id="warning">
            </div>
            <div id="positive-warning">
            </div>
            <button type="submit">Login</button>
            <button onclick="LOGIN_CreateAccount()">Create Account</button>
        </form>
    </section>
</div>`;



/// VERIFIES IF A USERNAME IS VALID ---------------------------------------------------------------------------------------------

var LOGIN_ValidUserName = str => {
    if ((typeof str) !== "string")
        return false;
    if (str.length == 0 || str.length > 100 ||
      str.match(/^[0-9a-z\._]*$/ig) === null)
        return false;
    return true;    
};



/// CALLS THE SIGNUP FUNCTIONS IF THE SIGNUP BUTTON IS PRESSED ------------------------------------------------------------------

/// if the "create account" button is pressed, it will call the "create acount" function
var LOGIN_CreateAccount = function() {
    SIGNUP_Signup(LOGIN_Login);
}



/// RECEIVES THE MESSAGE BACK FROM THE SERVER -----------------------------------------------------------------------------------

/// receives the message from the server and decides if it needs to call the callback function
var LOGIN_checker = function(obj) {
    if (obj.authentification.authentificated) {
        document.getElementById("warning").innerHTML = "";
        document.getElementById("positive-warning").innerHTML = "<p>Succesfully signed in. Redirecting to Login Page...</p>";
        setTimeout(function() { MENU_Menu(obj, LOGIN_Login); }, 1000);
    }
    else
        document.getElementById("warning").innerHTML = "<p>" + obj.authentification.message + "</p>";
}



/// VERIFIES IF THE INSERTED DATA IS VALID --------------------------------------------------------------------------------------

/// is called when the form is submited
var LOGIN_VerifyData = function() {
    var user = document.getElementById("username").value;
    if (!LOGIN_ValidUserName(user)) {
        document.getElementById("warning").innerHTML = "<p>Please enter a valid username</p>";
        return;
    }
    var password = document.getElementById("password").value;
    SYNC_SignIn(user, password, LOGIN_checker);
}



/// RENDERS THE HTML PAGE -------------------------------------------------------------------------------------------------------

/// creates the html
var LOGIN_Login = function() {
    // var obj = {
    //     info: {
    //         user: "alex",
    //         name: "name",
    //         password: "123123"
    //     },
    //     config: {
    //         sort_notes_by: "alphabetical",
    //         sort_asc: true,
    //         stay_signed_in: false,
    //         avatar_url: "images/avatar.jpg"
    //     },
    //     data: [{
    //         title: "Getting Started",
    //         task: "Work",
    //         creation_date: "2020-04-01",
    //         content: 'Welcome to the Notes apps!',
    //         asociated_picture: "Work/0.jpg"
    //     },
    //     {
    //         title: "Getting Started",
    //         task: "Work",
    //         creation_date: "2020-04-01",
    //         content: 'Welcome to the Notes apps!',
    //         asociated_picture: "Work/1.jpg"
    //     },
    //     {
    //         title: "Getting Started",
    //         task: "Work",
    //         creation_date: "2020-04-01",
    //         content: 'Welcome to the Notes apps!',
    //         asociated_picture: "Work/2.jpg"
    //     },
    //     {
    //         title: "Getting Started",
    //         task: "Work",
    //         creation_date: "2020-04-01",
    //         content: 'Welcome to the Notes apps!',
    //         asociated_picture: "Work/3.jpg"
    //     }
    // ]};

    // MENU_Menu(obj, LOGIN_Login);
    // return;
    var wrapper = document.getElementById('wrapper');
    wrapper.innerHTML = LOGIN_html_code;
}