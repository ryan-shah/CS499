$(document).ready(function () {

    $.ajaxSetup({   // Laravel requires this in order to make post requests
        headers: {
            'X-CSRF-TOKEN': $('meta[name="csrf-token"]').attr('content')
        }
    });

    function submitNewProgram() {
        $(".submit-program").click(function(){
            var data = {};
            var $inputs = $('.add-program-form :input');
            console.log($('.add-program-form').serializeArray());
            data = $('.add-program-form').serializeArray();

            console.log(data);
            $.post("/add", data, function (response) {
                console.log(response);
            }, 'json');
        });
    }

    submitNewProgram();
});


function editProgram(program_id){
    alert("Editing program with PID " + program_id);
}

function addRunlist(){
    alert("Runlist jazz happens");
}

function editRunlist(runlist_id){
    alert("Editing runlist with RPID " + runlist_id);
}