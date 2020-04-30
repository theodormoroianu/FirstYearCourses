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



/// CALLS THE SIGNUP FUNCTIONS IF THE SIGNUP BUTTON IS PRESSED ------------------------------------------------------------------

var LOGIN_CreateAccount = () => {
    SIGNUP_Signup(LOGIN_Login);
}



/// RECEIVES THE MESSAGE BACK FROM THE SERVER -----------------------------------------------------------------------------------

var LOGIN_checker = (obj) => {
    if (obj.authentification.authentificated) {
        document.getElementById("warning").innerHTML = "";
        document.getElementById("positive-warning").innerHTML = "<p>Succesfully signed in. Redirecting to Login Page...</p>";
        
        if (obj.config.stay_signed_in)
            window.localStorage.setItem('token', obj.info.token);
        
        setTimeout(function() { MENU_Menu(obj, LOGIN_Login); }, 1000);
    }
    else
        document.getElementById("warning").innerHTML = "<p>" + obj.authentification.message + "</p>";
}

var LOGIN_checker_localstorage = (obj) => {
    /// same function as above, except this one doesn't print any error messages
    if (obj.authentification.authentificated) {
        if (obj.config.stay_signed_in)
            window.localStorage.setItem('token', obj.info.token);
        MENU_Menu(obj, LOGIN_Login);
    }
}



/// VERIFIES IF THE INSERTED DATA IS VALID --------------------------------------------------------------------------------------

/// is called when the form is submited
var LOGIN_VerifyData = () => {
    var user = document.getElementById("username").value;
    var password = document.getElementById("password").value;
    SYNC_SignIn({
        user: user,
        password: password
    }, LOGIN_checker);
}



/// RENDERS THE HTML PAGE -------------------------------------------------------------------------------------------------------

var LOGIN_Login = () => {
    /// checks if the localstorage stores the username and password
    var x = window.localStorage.getItem('token');
    if (x !== null && x != undefined) {
        console.log("Found token " + x + " in localstorage");
        SYNC_SignIn({
            token: x
        }, LOGIN_checker_localstorage);
    }

    var wrapper = document.getElementById('wrapper');
    wrapper.innerHTML = LOGIN_html_code;
}