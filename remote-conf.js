var cdnjsURL = 'https://cdnjs.cloudflare.com/ajax/libs/',
    $;
(function()
{
    var script = document.createElement('script'); // create a <script> element
    script.src = cdnjsURL + 'jquery/3.2.1/jquery.min.js'; // set the src="" attribute
    script.onload = function() //callback function, called once jquery file is loaded
    {
        $ = window.jQuery; // make jQuery accessible as the global $ variable
        init(); // call the init function
    };
    document.getElementsByTagName('head')[0].appendChild(script); // add the created <script> tag to the document, this will start loading of the jQuery lib
})();

function init()
{
    // create a button and attach an eventlisteren for the `click` event:
    $('<button>').text('a button').on('click', function()
    {
        $.get('/ajax', function(data) // perform an async request on the /ajax url
        {
            $('<p>').text(data).appendTo('body'); // create a new <p> element containing the returned data and append it to the body of the page
        });
    }).appendTo('body'); // append the button element to the body of the page
}