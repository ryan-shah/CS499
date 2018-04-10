$(document).ready(function () {

    $.ajaxSetup({   // Laravel requires this in order to make post requests
        headers: {
            'X-CSRF-TOKEN': $('meta[name="csrf-token"]').attr('content')
        }
    });

    function handleProgram() {
        $(".modal-submit").click(function () {
            // var data = $('.add-program-form').serializeArray();
            var form_id = $(this).attr('id');
            var data = $('form[id=' + form_id + ']').serializeArray();
            console.log(data);
            $.post(form_id, data, function (response) { // This will handle both creating a new program and updating an old one
                console.log(response);
            }, 'json');
        });
    }

    function getProgramInfo() {
        $(".begin-edit").click(function () {
            var program_id = $(this).attr('id');
            console.log("Edit clicked");
            $.post('get-program/' + program_id, null, function (response) {
                var program = JSON.parse(response['program']);
                var edit_modal = $('#editProgramModal');    // Display all of the current data for the program selected
                edit_modal.find('#name').val(program['pname']);
                edit_modal.find('#path').val(program['path']);
                edit_modal.find('#memUsage').val(program['estimated_memory_usage']);
                edit_modal.find('#dependencies').val("TODO");
                edit_modal.find('#runlist').val("TODO");
                edit_modal.find('#args').val(program['command_line']);
                edit_modal.find('#pid').val(program_id);
                edit_modal.modal('show');
            });
        });
    }

    getProgramInfo();
    handleProgram();
});


function editProgram(program_id) {

}

function addRunlist() {
    alert("Runlist jazz happens");
}

function editRunlist(runlist_id) {
    alert("Editing runlist with RPID " + runlist_id);
}