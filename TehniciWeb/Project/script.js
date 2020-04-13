function getInputValue(){
    // Selecting the input element and get its value 
    var inputVal = document.getElementById("textbox").value;
    
    // Displaying the value
    console.log(inputVal);

    setTimeout(getInputValue, 1000);
}

getInputValue()