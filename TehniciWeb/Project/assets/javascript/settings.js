/**
 * This script helps creating and modifying SETTINGS
 */

 /// THIS IS THE DEFAULT HTML CODE FOR THE SETTINGS -----------------------------------------------------------------------------

 SETTINGS_html_code =
`
<header id="header">
<h1 style='text-align:center;border:10px 10px;'>Welcome to the SETTINGS editor!</h1>
</header>        
<form action='#' onsubmit="SETTINGS_ProcessChanges();return false">
    <label for="name"><b>Name</b></label>
    <input type="text" placeholder="Enter Your Name Here" name="name" id='name' required>
    
    <input type='checkbox' id='stay-signed-in'
        name ='stay-signed-in' value="Stay Signed In"/>
    <label for='stay-signed-in'><b>Stay Signed In</b></label>
    
    <label for="new-password"><b>New password</b></label>
    <input type="password" placeholder="Enter Your New Password" name="new-password" id='new-password'>
    <input type="password" placeholder="Enter Your New Password Again" name="new-password-repeat" id='new-password-repeat'>
       
    <label for='choose-avatar'><b>Avatar Picture</b></label>
    <input type="text" placeholder="Enter Your Avatar Link Here" name="choose-avatar" id='choose-avatar' required>


    <label for="notes-order"><b>Sort Notes By</b></label>
    <select class="custom-select" name="notes-order" id='notes-order' required>
        <option value ="Deadline" class="dropdown-menu">Deadline</option>
        <option value ="Creation Date" class="dropdown-menu">Creation Date</option>
        <option value ="Alphabetical" class="dropdown-menu">Alphabetical</option>
    </select> 
        
    <input type='checkbox' id='sort-notes-asc'
        name ='sort-notes-asc' value='sort-notes-asc'/>
    <label for='sort-notes-asc'><b>Sort Notes in Ascendig order</b></label>
    </br>
    <div id="warning">
    </div>
    <div id="positive-warning">
    </div>
    <button type="submit">Save</button>
    <button onclick="SETTINGS_Discard()">Discard</button>
</form>`;
 
 
 
/// SIDE FUNCTIONS NEEDED -------------------------------------------------------------------------------------------------------

var SETTINGS_callback = null;
var SETTINGS_object = null;



/// FUNCTION PROCESSING CHANGES -------------------------------------------------------------------------------------------------

var SETTINGS_ProcessChanges = function() {
    var name = document.getElementById('name').value;
    var stay_signed_in = document.getElementById('stay-signed-in').checked;
    var avatar = document.getElementById('choose-avatar').value;
    var notes_order = document.getElementById('notes-order').value;
    var sort_asc = document.getElementById('sort-notes-asc').checked;
    var new_password = document.getElementById('new-password').value;
    var new_password_repeat = document.getElementById('new-password-repeat').value;
    if (name.length > 20) {
        document.getElementById("warning").innerHTML = "<p>The name is too long</p>";
        return;
    }
    if (new_password.length + new_password_repeat.length > 0) {
        if (new_password !== new_password_repeat) {
            document.getElementById("warning").innerHTML = "<p>The passwords don't match</p>";
            return;
        }
        if (new_password.length < 6) {
            document.getElementById("warning").innerHTML = "<p>The password is too short</p>";
            return;
        }
    }

    SETTINGS_object.info.name = name;
    SETTINGS_object.config.stay_signed_in = stay_signed_in;
    SETTINGS_object.config.avatar_url = avatar;
    SETTINGS_object.config.sort_notes_by = notes_order;
    SETTINGS_object.config.sort_asc = sort_asc;

    if (new_password.length > 0)
        SETTINGS_object.info['password'] = new_password;

    document.getElementById("warning").innerHTML = "";
    document.getElementById("positive-warning").innerHTML = "<p>Saved Changes! Going back to main menu...</p>";

    window.onbeforeunload = function() { }

    /// clear localstorage
    window.localStorage.clear();

    /// if enabled, store the creditentials in storage
    if (stay_signed_in)
        window.localStorage.setItem('token', SETTINGS_object.info.token);

    setTimeout(SETTINGS_callback, 1000);
}



/// FUNCTION DISCARDING CHANGES THE SETTINGS ------------------------------------------------------------------------------------

var SETTINGS_Discard = function() {
    window.onbeforeunload = function() { }
    SETTINGS_callback();
}



/// FUNCTION CREATING THE SETTINGS ----------------------------------------------------------------------------------------------

var SETTINGS_Settings = function(obj, callback) {
    window.onbeforeunload = function() {
        return 'Are you sure you want to leave?';
    };

    SETTINGS_callback = callback;
    SETTINGS_object = obj;
 
    var wrapper = document.getElementById('wrapper');
    wrapper.innerHTML = SETTINGS_html_code;

    document.getElementById('name').value = obj.info.name;
    document.getElementById('stay-signed-in').checked = obj.config.stay_signed_in;
    document.getElementById('choose-avatar').value = obj.config.avatar_url;
    document.getElementById('notes-order').value = obj.config.sort_notes_by;
    document.getElementById('sort-notes-asc').checked = obj.config.sort_asc;
}