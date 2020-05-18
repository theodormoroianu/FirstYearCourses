/**
 * This script helps modifying notes
 */
 EDITOR_html_code =
`<h1 class='h1' style='text-align:center;border:10px 10px;'>Welcome to the Note editor!</h1>
    <form class='form' action='#' onsubmit="return false">
    <label class='label' for="note_name"><b class='b'>Title of the Note</b></label>
    <input class='input' type="text" placeholder="Enter Title Here" name="note_name" id="note_name">

    <label class="label" for="note_type"><b class='b'>Type of the note</b></label>
    <select class="custom-select select" name="note_type" id="note_type">
        <option value="Work" class="dropdown-menu">Work</option>
        <option value="Family" class="dropdown-menu">Family</option>
        <option value="Cooking" class="dropdown-menu">Cooking</option>
        <option value="Traveling" class="dropdown-menu">Traveling</option>
        <option value="Having Fun" class="dropdown-menu">Having Fun</option>
    </select> 

    <label class="label" for="deadline"><b class='b'>Deadline</b></label>
    <input class="input" type="date" id="deadline" name="deadline">
    <label class="label" for="content"><b class='b'>Content</b></label>       
    <textarea class="textarea content-textbox" name="content" cols="40" rows="10" id="content-textbox"></textarea>
    <div id="warning" class="warning">
    </div>
    <div id="positive-warning" class="positive-warning">
    </div>
    <button class="button" onclick="EDITOR_ProcessChanges()">Save</button>
    <button class="button" onclick="EDITOR_Discard()">Discard Changes</button>
    <button class="button" onclick="EDITOR_Delete()">Delete Note</button>
</form>`;
 
 
 
/// SIDE FUNCTIONS NEEDED -------------------------------------------------------------------------------------------------------

var EDITOR_callback = null;
var EDITOR_object = null;
var EDITOR_id = null;


/// FUNCTION PROCESSING CHANGES

var EDITOR_ProcessChanges = function() {
    var title = document.getElementById("note_name").value;
    if (title.length > 20) {
        document.getElementById("warning").innerHTML = "<p>The title is too long!</p>";
        return;
    }
    if (title.length == 0) {
        document.getElementById("warning").innerHTML = "<p>The note must have a title!</p>";
        return;
    }
    var deadline = document.getElementById("deadline").value;
    var content = document.getElementById("content-textbox").value;
    var note_type = document.getElementById("note_type").value;

    if (note_type.length == 0) {
        document.getElementById("warning").innerHTML = "<p>The note must have a type!</p>";
        return;
    }

    EDITOR_object.head = EDITOR_object.versions.length;
    EDITOR_object.versions.push({
        title: title,
        deadline: deadline,
        content: content,
        task: note_type,
        asociated_picture: note_type + '/' + Math.floor(Math.random() * 6) + ".jpg",
        origin: EDITOR_id
    });

    document.getElementById("warning").innerHTML = "";
    document.getElementById("positive-warning").innerHTML = "<p>Saved Changes! Going back to main menu...</p>";

    
    window.onbeforeunload = function() { }
    setTimeout(EDITOR_callback, 1000);
}



/// FUNCTION DELETING THE NOTE ------------------------------------------------------------------------------------------------

var EDITOR_Delete = function() {
    NOTE_object.head = -1;
    /// it should self-distruct without a title
    window.onbeforeunload = function() { }
    document.getElementById("warning").innerHTML = "";
    document.getElementById("positive-warning").innerHTML = "<p>Note Deleted! Going back to main menu...</p>";

    window.onbeforeunload = function() { }
    setTimeout(EDITOR_callback, 1000);
}



/// FUNCTION DISCARDING CHANGES THE NOTE ------------------------------------------------------------------------------------------------

var EDITOR_Discard = function() {
    document.getElementById("warning").innerHTML = "";
    document.getElementById("positive-warning").innerHTML = "<p>Changes Discarded! Going back to main menu...</p>";

    window.onbeforeunload = function() { }
    setTimeout(EDITOR_callback, 1000);
}



/// FUNCTION CREATING THE NOTE --------------------------------------------------------------------------------------------------

var EDITOR_Editor = function(callback, obj, id) {
    window.onbeforeunload = function() {
        return 'Are you sure you want to leave?';
    };

    EDITOR_callback = callback;
    EDITOR_object = obj;
    EDITOR_id = id;
 
    var wrapper = document.getElementById('wrapper');
    wrapper.innerHTML = EDITOR_html_code;

    if (id != -1) {
        document.getElementById("note_name").value = obj.versions[id].title;
        document.getElementById("deadline").value = obj.versions[id].deadline;
        document.getElementById("content-textbox").value = obj.versions[id].content;
        document.getElementById("note_type").value = obj.versions[id].task;
    }
}