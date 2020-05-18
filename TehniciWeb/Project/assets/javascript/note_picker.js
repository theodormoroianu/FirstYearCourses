/**
 * This script helps choosing which version to edit
 */

 /// THIS IS THE DEFAULT HTML CODE FOR THE NOTES ---------------------------------------------------------------------------------

 PICKER_html_code =
`<h1 class='h1' style='text-align:center;border:10px 10px;'>Please choose which version you want to edit!</h1>
    <div class="list" id="graph">        
    </div>
    <section class="thumbnails list section" id="list">        
    </section>
    <form class='form' action='#' onsubmit="return false">
    <div id="warning" class="warning">
    </div>
    <div id="positive-warning" class="positive-warning">
    </div>
    <button class="button" onclick="PICKER_Exit()">Exit</button>
    <button class="button" onclick="PICKER_Delete()">Delete Note</button>
</form>`;
 
 
 
/// SIDE FUNCTIONS NEEDED -------------------------------------------------------------------------------------------------------

var PICKER_callback = null;
var PICKER_object = null;
var PICKER_unique_id = 0;

/// FUNCTION DELETING THE NOTE ------------------------------------------------------------------------------------------------

var PICKER_Delete = function() {
    NOTE_object.head = -1;
    /// it should self-distruct without a title
    window.onbeforeunload = function() { }
    document.getElementById("warning").innerHTML = "";
    document.getElementById("positive-warning").innerHTML = "<p>Note Deleted! Going back to main menu...</p>";

    window.onbeforeunload = function() { }
    setTimeout(NOTE_callback, 1000);
}



/// FUNCTION EXITINGING CHANGES THE NOTE ------------------------------------------------------------------------------------------------

var PICKER_Exit = function() {
    window.onbeforeunload = function() { }
    document.getElementById("warning").innerHTML = "";
    document.getElementById("positive-warning").innerHTML = "<p>Going back to main menu...</p>";

    window.onbeforeunload = function() { }
    setTimeout(NOTE_callback, 1000);
}



/// FUNCTION PROCESSING THE VERSION EDITION -------------------------------------------------------------------------------------

var PICKER_EditNote = (id) => {
    EDITOR_Editor(PICKER_callback, PICKER_object, id);
}



/// FUNCTION RENDERING VERSIONS OF THE NOTE -------------------------------------------------------------------------------------

var PICKER_RenderVersions = () => {
    /// creating graph
    const graph = document.getElementById('graph');
    var image = document.createElement('img');
    image.setAttribute('src', 'API/note_graph?note_id=' + PICKER_object.note_id + "&useless_id=" + (PICKER_unique_id++));
    graph.appendChild(image);
    graph.setAttribute("style", "mix-blend-mode: multiply;padding-bottom: 100px;");
    
    const list = document.getElementById('list');

    for (var i = 0; i < PICKER_object.versions.length; i++) {
        obj = PICKER_object.versions[i];
        
        var a = document.createElement('a');
        a.setAttribute('href', 'javascript:PICKER_EditNote(' + i + ')');
        a.setAttribute('class', 'image a');

        var title = document.createElement('h3');
        title.setAttribute('class', 'h3');
        title.textContent = "Version #" + i + ": " + obj.title;

        a.appendChild(title);

        list.appendChild(a);
    }
}




/// FUNCTION CREATING THE NOTE --------------------------------------------------------------------------------------------------

var PICKER_Picker = function(obj, callback) {
    PICKER_callback = callback;
    PICKER_object = obj;
    
    if (obj.head == -1) {
        PICKER_EditNote(-1);
        return;
    }

    var wrapper = document.getElementById('wrapper');
    wrapper.innerHTML = PICKER_html_code;

    PICKER_RenderVersions();
}