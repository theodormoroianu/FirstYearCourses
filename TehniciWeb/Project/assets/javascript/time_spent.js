var TIME_SPENT_login_time = undefined;

var TIME_SPENT_compute = () => {
    var time = parseInt(window.localStorage.getItem('total-time'));
    window.localStorage.setItem('total-time', time + 1);

    var hours = String(Math.floor(time / 3600)) + " hours ";
    var minutes = String(Math.floor(time / 60 % 60)) + " min ";
    var seconds = String(Math.floor(time % 60)) + " sec";
    document.getElementById('time_spent').innerText = hours + minutes + seconds;
    setTimeout(TIME_SPENT_compute, 1000);
}

/// we have 30 min of active session
var TIME_SPENT_time_left_compute = () => {
    var time = 30 * 60 - Math.floor((Date.now() - TIME_SPENT_login_time) / 1000);
    if (time <= 0) {
        MENU_SignOut();
        document.getElementById('time_left').innerText = '-';
        return;
    }
    if (MENU_object === undefined) {
        document.getElementById('time_left').innerText = '-';
        return;
    }

    // var hours = String(Math.floor(time / 3600)) + " hours ";
    var minutes = String(Math.floor(time / 60 % 60)) + " min ";
    var seconds = String(Math.floor(time % 60)) + " sec";
    document.getElementById('time_left').innerText = minutes + seconds;
    setTimeout(TIME_SPENT_time_left_compute, 1000);
}

/// starts the timer that counts time left until signout
var TIME_SPENT_time_left_start = () => {
    TIME_SPENT_login_time = Date.now();
    TIME_SPENT_time_left_compute();
}


// Starts the timer that counts the time spent on the website
var TIME_SPENT_start = () => {
    var x = window.localStorage.getItem('total-time');
    if (x == null || x == undefined || x == "NaN")
        window.localStorage.setItem('total-time', 0);
    TIME_SPENT_compute();
}
