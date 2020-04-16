/**
 * This script creates basically all the main menu html
 */

 /// THIS IS THE DEFAULT HTML CODE FOR THE MENU ---------------------------------------------------------------------------------

MENU_html_code =
`<!-- Header -->
<header id="header">
    <span class="avatar" id='avatar'></span>
    <h1>Hi <my_tag id="name"></my_tag>! We're exited to have you back. You have <a id="count-notes">a few</a>
    notes, out of which <a id="count-exact-deadline">a few</a>
    have their deadline today and <a id="count-passed-deadline">a few</a> are past their deadline.</h1>
    <ul class="icons">
        <li><a href="javascript:MENU_Note(-1)"><span class="label">New Task</span></a></li>
        <li><a href="javascript:MENU_Settings()"><span class="label">Settings</span></a></li>
        <li><a href="javascript:MENU_Credits()"><span class="label">Credits</span></a></li>
        <li><a href="javascript:MENU_SignOut()"><span class="label">Sign Out</span></a></li>
    </ul>
</header>

<section class="thumbnails" id="list">        
</section>`;



/// SIDE FUNCTIONS NEEDED -------------------------------------------------------------------------------------------------------

var MENU_callback = null;
var MENU_object = null;

var MENU_SignOut = function() {
    MENU_object = null; /// distroy the object
    MENU_callback();
}



/// FUNCTION CALLING THE SETTINGS PAGE ------------------------------------------------------------------------------------------

var MENU_Settings = function() {
    SETTINGS_Settings(MENU_object, function() {
        SYNC_Checkpoint(MENU_object, (obj) => {
            if (obj.authentification.authentificated)
                console.log("Created checkpoint");
            else
                console.log("Error while creating checkpoint");
        });
        MENU_Menu();
    });
}



/// FUNCTION SHOWING THE CREDITS ------------------------------------------------------------------------------------------------

var MENU_Credits = function() {
    CREDITS_Credits(MENU_object, MENU_Menu);
}



/// FUNCTION CALLING THE NOTES PAGE ---------------------------------------------------------------------------------------------

var MENU_Note = function(id) {
    /// must show the id-th note
    if (id == -1) {
        /// I must create a new note
        MENU_object.data.push({
            title: "",
            task: "",
            creation_date: Date.now(),
            content: '',
            asociated_picture: ""
        })
        id = MENU_object.data.length - 1;
    }
    NOTE_Note(MENU_object.data[id], function() {
        if (MENU_object.data[id].title.length == 0) { /// must delete the note
            MENU_object.data[id] =
                MENU_object.data[MENU_object.data.length - 1];
            MENU_object.data.pop();
        }
        SYNC_Checkpoint(MENU_object, (obj) => {
            if (obj.authentification.authentificated)
                console.log("Created checkpoint");
            else
                console.log("Error while creating checkpoint");
        });
        MENU_Menu();
    });
}



/// RENDERS THE NOTES TO THE PAGE --------------------------------------------------------------------------------------------------

var MENU_RenderNotes = function() {
    MENU_object.data.sort((a, b) => {
        var asmall = false;
        if (MENU_object.config.sort_note_by == 'Deadline')
            asmall = (a.deadline < b.deadline);
        else if (MENU_object.config.sort_note_by == 'Creation Date')
            asmall = (a.creation_date < b.creation_date);
        else if (MENU_object.config.sort_note_by == 'Alphabetical')
            asmall = (a.title < b.title);
        
        if (!MENU_object.config.sort_asc)
            asmall = !asmall;
        if (asmall)
            return -1;
        return 1;
    });

    for (var i = 0; i < MENU_object.data.length; i++) {
        obj = MENU_object.data[i];
        var content = `<a href="javascript:MENU_Note(` + i + `)" class='image'>
            <img src="images/` + obj.asociated_picture + `" alt="image"/>
            <h3>` + obj.title + `</h3>
            </a>`;
        document.getElementById('list').innerHTML += content;
    }
}


/// FUNCTION CREATING THE MENU PAGE --------------------------------------------------------------------------------------------

var MENU_Menu = function(obj, callback) {
    if (callback !== null && callback !== undefined)
        MENU_callback = callback;
    if (obj !== null && obj !== undefined)
        MENU_object = obj;

    console.log("Entered menu. Obj = ");
    console.log(MENU_object);

    var wrapper = document.getElementById('wrapper');
    wrapper.innerHTML = MENU_html_code;

    var date_now = (new Date()).toISOString().slice(0,10);
    var deadline_today = 0;
    var deadline_passed = 0;

    for (var i = 0; i < MENU_object.data.length; i++) {
        if (MENU_object.data[i].deadline.length == 10) {
            if (MENU_object.data[i].deadline == date_now)
                deadline_today++;
            if (MENU_object.data[i].deadline < date_now)
                deadline_passed++;
        }
    }

    document.getElementById('count-notes').innerHTML = MENU_object.data.length;
    document.getElementById('count-exact-deadline').innerHTML = deadline_today;
    document.getElementById('count-passed-deadline').innerHTML = deadline_passed;
    document.getElementById('name').innerHTML = MENU_object.info.name;
    document.getElementById('avatar').innerHTML = "<img src='" + MENU_object.config.avatar_url + "' alt='avatar'/>";

    MENU_RenderNotes();
}