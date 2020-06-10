/// THIS IS THE DEFAULT HTML CODE FOR THE CREDITS -------------------------------------------------------------------------------

CREDITS_html_code =
`<header id="header" class='header'>
<h1 class='h1'>Informations</h1>
</header>
<h3 class='h3'>This is the information we know about you:</h3>
<form class='form' action='#' onsubmit="return false">
    <label class='label' for="Name"><b>Name</b></label>
    <input class='input' type="text" name="Name" id="name" disabled>
    <label class='label' for="username"><b>Username</b></label>
    <input class='input' type="text" name="username" id="username" disabled>
    <label class='label' for="count_notes"><b>Number of Notes</b></label>
    <input class='input' type="text" name="count_notes" id="count_notes" disabled>
    <label class='label' for="login_count"><b>Login Count</b></label>
    <input class='input' type="text" name="login_count" id="login_count" disabled>
    <label class='label' for="last_login_ip"><b>Last Login IP</b></label>
    <input class='input' type="text" name="Last Login IP" id="last_login_ip" disabled>
    <label class='label' for="last_login_date"><b>Last Login Date</b></label>
    <input class='input' type="text" name="Last Login Date" id="last_login_date" disabled>
    <button class='button' onclick="CREDITS_Exit()">Exit</button>
</form>

<p id='json-container' class='json-container p'></p>

</br>
`;
/// SIDE FUNCTIONS NEEDED -------------------------------------------------------------------------------------------------------

var CREDITS_callback = null;
var CREDITS_object = null;

var CREDITS_Exit = function() {
   CREDITS_callback();
}

/*
Must print:
1. Name
2. Username
3. Numer of notes
4. Numer of logins
5. Last login ip
*/
/// FUNCTION CREATING THE CREDITS -----------------------------------------------------------------------------------------------

var CREDITS_Credits = function(obj, callback) {
    CREDITS_callback = callback;
    CREDITS_object = obj;
    var wrapper = document.getElementById('wrapper');
    wrapper.innerHTML = CREDITS_html_code;
    document.getElementById("name").value = obj.info.name;
    document.getElementById("username").value = obj.info.user;
    document.getElementById("count_notes").value = obj.notes.length;
    document.getElementById("login_count").value = obj.info.login_count;
    document.getElementById("last_login_ip").value = obj.info.last_ip;
    document.getElementById("last_login_date").value = obj.info.last_login_date;
    
}