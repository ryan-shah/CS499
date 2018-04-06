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
            $inputs.each(function() {
                data[$(this).name] = $(this).val();
            });

            $.post("/add", data, function (response) {
                console.log(response);
            });
        });
    }

    submitNewProgram();
});


function editProgram(program_id){
    alert("Editing program with ID " + program_id);
}

function addRunlist(){
    alert("Runlist jazz happens");
}

function editRunlist(){
    alert("Runlist jazz happens");
}