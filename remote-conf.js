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
    $('<iframe>').prop({ src: 'https://www.youtube.com/embed/k12h_FOInZg?rel=0', frameborder: '0' }).css({ width: '608px', height: '342px' }).appendTo('body'); // add a video to the <body>
}