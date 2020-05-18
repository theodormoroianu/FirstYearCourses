/**
 * This script displays a note
 */

 /// THIS IS THE DEFAULT HTML CODE FOR THE NOTES ---------------------------------------------------------------------------------

 NOTE_html_code =
`<h1 class='h1' style='text-align:center;border:10px 10px;'>Welcome to the Note preview! The last version of the note is:</h1>
    <form class='form' action='#' onsubmit="return false">
    <label class='label' for="note_name"><b class='b'>Title of the Note</b></label>
    <input class='input' type="text" placeholder="Enter Title Here" name="note_name" id="note_name" disabled>

    <label class="label" for="note_type"><b class='b'>Type of the note</b></label>
    <select class="custom-select select" name="note_type" id="note_type" disabled>
        <option value="Work" class="dropdown-menu">Work</option>
        <option value="Family" class="dropdown-menu">Family</option>
        <option value="Cooking" class="dropdown-menu">Cooking</option>
        <option value="Traveling" class="dropdown-menu">Traveling</option>
        <option value="Having Fun" class="dropdown-menu">Having Fun</option>
    </select> 

    <label class="label" for="deadline"><b class='b'>Deadline</b></label>
    <input class="input" type="date" id="deadline" name="deadline" disabled>
    <label class="label" for="content"><b class='b'>Content</b></label>       
    <textarea class="textarea content-textbox" name="content" cols="40" rows="10" id="content-textbox" disabled></textarea>
    <div id="warning" class="warning">
    </div>
    <div id="positive-warning" class="positive-warning">
    </div>
    <button class="button" onclick="NOTE_Exit()">Exit</button>
    <button class="button" onclick="NOTE_Delete()">Delete Note</button>
    <button class="button" onclick="NOTE_EditNote()">Edit Note</button>
</form>`;
 
 
 
/// SIDE FUNCTIONS NEEDED -------------------------------------------------------------------------------------------------------

var NOTE_callback = null;
var NOTE_object = null;


/// FUNCTION DELETING THE NOTE ------------------------------------------------------------------------------------------------

var NOTE_Delete = function() {
    NOTE_object.head = -1;
    /// it should self-distruct without a title
    window.onbeforeunload = function() { }
    document.getElementById("warning").innerHTML = "";
    document.getElementById("positive-warning").innerHTML = "<p>Note Deleted! Going back to main menu...</p>";

    window.onbeforeunload = function() { }
    setTimeout(NOTE_callback, 1000);
}



/// FUNCTION EXITINGING CHANGES THE NOTE ------------------------------------------------------------------------------------------------

var NOTE_Exit = function() {
    window.onbeforeunload = function() { }
    document.getElementById("warning").innerHTML = "";
    document.getElementById("positive-warning").innerHTML = "<p>Going back to main menu...</p>";

    setTimeout(NOTE_callback, 1000);
}



/// EDIT NOTE ----------------------------------------------------------------------------------------------------------------

var NOTE_EditNote = () => {
    PICKER_Picker(NOTE_object, NOTE_callback);
}



/// FUNCTION CREATING THE NOTE --------------------------------------------------------------------------------------------------

var NOTE_Note = function(obj, callback) {    
    NOTE_callback = callback;
    NOTE_object = obj;
    
    if (obj.head == -1) {
        /// empty note
        NOTE_EditNote();
        return;
    }

    var wrapper = document.getElementById('wrapper');
    wrapper.innerHTML = NOTE_html_code;

    var note = obj.versions[obj.head];

    document.getElementById("note_name").value = note.title;
    document.getElementById("deadline").value = note.deadline;
    document.getElementById("content-textbox").value = note.content;
    document.getElementById("note_type").value = note.task;
}