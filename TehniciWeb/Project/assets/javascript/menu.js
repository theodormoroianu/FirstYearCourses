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
var notes = [];

var MENU_SignOut = function() {
    SYNC_SignOut({
        token: MENU_object.info.token
    }, () => { });

    delete MENU_object;
    window.localStorage.clear();
    MENU_callback();
}



/// FUNCTION CALLING THE SETTINGS PAGE ------------------------------------------------------------------------------------------

var MENU_Settings = () => {
    SETTINGS_Settings(MENU_object, () => {
        var new_settings = {
            token: MENU_object.info.token,
            info: {
                name: MENU_object.info.name,
            },
            config: MENU_object.config
        };
        if (MENU_object.info.hasOwnProperty('password')) {
            new_settings.info['password'] = MENU_object.info.password;
            delete MENU_object.info.password;
        }

        SYNC_UpdateSettings(new_settings, (obj) => {
            if (obj.authentification.authentificated)
                console.log("saved settings");
            else
                console.log("Error while saving settings");
        });
        MENU_Menu();
    });
}



/// FUNCTION SHOWING THE CREDITS ------------------------------------------------------------------------------------------------

var MENU_Credits = () => {
    CREDITS_Credits(MENU_object, MENU_Menu);
}



/// FUNCTION CALLING THE NOTES PAGE ---------------------------------------------------------------------------------------------

var MENU_Note = (id) => {
    /// must show the id-th note
    if (id == -1) {
        /// I must create a new note
        notes.push({
            title: "",
            task: "",
            creation_date: Date.now(),
            content: '',
            asociated_picture: ""
        })
        id = notes.length - 1;
    }
    NOTE_Note(notes[id], function() {
        if (notes[id].title.length == 0) { /// must delete the note
            if (notes[id].hasOwnProperty('note_id')) {
                SYNC_DeleteNote({
                    token: MENU_object.info.token,
                    note_id: notes[id].note_id
                }, () => { });
                MENU_object.notes = MENU_object.notes.filter(note => {
                    return note.note_id !== notes[id].note_id;
                });
                MENU_Menu();
            }
        }
        else if (!notes[id].hasOwnProperty('note_id')) {
            SYNC_CreateNote({
                token: MENU_object.info.token,
                data: notes[id]
            }, (obj) => {
                MENU_object.notes.push(obj.note_id);
                MENU_Menu();
            });
        }
        else {
            SYNC_UpdateNote({
                token: MENU_object.info.token,
                data: notes[id]
            }, () => {
                MENU_Menu();
            })
        }
    });
}



/// RENDERS THE NOTES TO THE PAGE --------------------------------------------------------------------------------------------------

var MENU_RenderNotes = function() {
    notes.sort((a, b) => {
        var asmall = false;
        if (MENU_object.config.sort_notes_by == 'Deadline')
            asmall = (a.deadline < b.deadline);
        else if (MENU_object.config.sort_notes_by == 'Creation Date')
            asmall = (a.creation_date < b.creation_date);
        else if (MENU_object.config.sort_notes_by == 'Alphabetical')
            asmall = (a.title < b.title);
        
        if (!MENU_object.config.sort_asc)
            asmall = !asmall;
        if (asmall)
            return -1;
        return 1;
    });

    const list = document.getElementById('list');

    for (var i = 0; i < notes.length; i++) {
        obj = notes[i];
        
        var a = document.createElement('a');
        a.setAttribute('href', 'javascript:MENU_Note(' + i + ')');
        a.setAttribute('class', 'image');

        var image = document.createElement('img');
        image.setAttribute('src', 'images/' + obj.asociated_picture);

        var title = document.createElement('h3');
        title.textContent = obj.title;

        a.appendChild(image);
        a.appendChild(title);

        list.appendChild(a);
    }
}



/// GET NOTES

var MENU_GetNotes = async () => {
    for (var i = 0; i < MENU_object.notes.length; i++) {
        var act = await SYNC_GetNote({
            token: MENU_object.info.token,
            note_id: MENU_object.notes[i]
        });
        notes.push(act.data);
    };
}

/// FUNCTION CREATING THE MENU PAGE --------------------------------------------------------------------------------------------

var MENU_Menu = (obj, callback) => {
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

    notes = []
    MENU_GetNotes().then(() => {
        for (var i = 0; i < notes.length; i++) {
            if (notes[i].deadline.length == 10) {
                if (notes[i].deadline == date_now)
                    deadline_today++;
                if (notes[i].deadline < date_now)
                    deadline_passed++;
            }
        }

        document.getElementById('count-notes').innerHTML = MENU_object.notes.length;
        document.getElementById('count-exact-deadline').innerHTML = deadline_today;
        document.getElementById('count-passed-deadline').innerHTML = deadline_passed;
        document.getElementById('name').innerHTML = MENU_object.info.name;
        document.getElementById('avatar').innerHTML = "<img src='" + MENU_object.config.avatar_url + "' alt='avatar'/>";

        MENU_RenderNotes();
    });
}