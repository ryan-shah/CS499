$(document).ready(function () {

    $.ajaxSetup({   // Laravel requires this in order to make post requests
        headers: {
            'X-CSRF-TOKEN': $('meta[name="csrf-token"]').attr('content')
        }
    });

    function addProgram() {
        $(".savestuff").click(function(){
            var data = {
                blah: "Yo"
            };
            $.post("/", data, function (response) {
                console.log(response);
            });
        });
    }

    addProgram();
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