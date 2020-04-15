/**
 * This script creates basically all the main menu html
 */

MENU_html_code =
`<!-- Header -->
<header id="header">
    <span class="avatar"><img src="images/avatar.jpg" alt="" /></span>
    <h1>This is <strong>Visualize</strong>, a responsive site template designed by <a href="http://templated.co">TEMPLATED</a><br />
    and released for free under the Creative Commons License.</h1>
    <ul class="icons">
        <li><a href="javascript:MENU_sample()"><span class="label">New Task</span></a></li>
        <li><a href="javascript:MENU_sample()"><span class="label">Settings</span></a></li>
        <li><a href="javascript:MENU_sample()"><span class="label">Sign Out</span></a></li>
        <li><a href="javascript:MENU_sample()"><span class="label">Credits</span></a></li>
    </ul>
</header>

<!-- Main -->
<section id="main">
    
    <!-- Thumbnails -->
        <section class="thumbnails">
            <div>
                <a href="images/fulls/03.jpg">
                    <img src="images/thumbs/03.jpg" alt="" />
                    <h3>Lorem ipsum dolor sit amet</h3>
                </a>
                <a href="images/fulls/04.jpg">
                    <img src="images/thumbs/04.jpg" alt="" />
                    <h3>Lorem ipsum dolor sit amet</h3>
                </a>
                <a href="images/fulls/05.jpg">
                    <img src="images/thumbs/05.jpg" alt="" />
                    <h3>Lorem ipsum dolor sit amet</h3>
                </a>
            </div>
            <div>
                <a href="images/fulls/01.jpg">
                    <img src="images/thumbs/01.jpg" alt="" />
                    <h3>Lorem ipsum dolor sit amet</h3>
                </a>
                <a href="images/fulls/02.jpg">
                    <img src="images/thumbs/02.jpg" alt="" />
                    <h3>Lorem ipsum dolor sit amet</h3>
                </a>
            </div>
            <div>
                <a href="images/fulls/06.jpg">
                    <img src="images/thumbs/06.jpg" alt="" />
                    <h3>Lorem ipsum dolor sit amet</h3>
                </a>
                <a href="images/fulls/07.jpg">
                    <img src="images/thumbs/07.jpg" alt="" />
                    <h3>Lorem ipsum dolor sit amet</h3>
                </a>
            </div>
        </section>

</section>

<!-- Footer -->
<footer id="footer">
    <p>&copy; Untitled. All rights reserved. Design: <a href="http://templated.co">TEMPLATED</a>. Demo Images: <a href="http://unsplash.com">Unsplash</a>.</p>
</footer>
`;

var MENU_callback = null;

var MENU_sample = function() {
    console.log("Yep");
}

var MENU_Menu = function(obj, callback) {
    MENU_callback = callback;

    var wrapper = document.getElementById('wrapper');
    wrapper.innerHTML = MENU_html_code;
}