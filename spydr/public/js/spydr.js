$(document).ready(function () {

    $.ajaxSetup({   // Laravel requires this in order to make post requests
        headers: {
            'X-CSRF-TOKEN': $('meta[name="csrf-token"]').attr('content')
        }
    });

    function handleProgram() {
        // Generic function for committing forms to the database.
        // This handles adding and editing programs, both in one function
        $(".program-modal-submit").click(function () {
            var form_id = $(this).attr('id');
            var data = $('form[id=' + form_id + ']').serializeArray();
            var formatted_data = [{name: 'dependencies', value: []}]; // We need to make an object for the dependencies

            // There's probably a cleaner way to add all of these, but this works I guess
            data.forEach(function(element){
                if(element['name'] === 'dependencies'){
                    console.log(formatted_data[0]['value']);
                    formatted_data[0]['value'].push(element['value']);
                } else {
                    formatted_data.push(element);
                }
            });

            formatted_data[0]['value'] = JSON.stringify(formatted_data[0]['value']);
            console.log(data);
            console.log(formatted_data);
            $.post(form_id, formatted_data, function (response) { // This will handle both creating a new program and updating an old one
                console.log(response);
            }, 'json');

            setTimeout(function(){
                location.reload();  // Easiest way to get the changes to show: refresh the page. Might change this later.
            }, 1000);
        });
    }

    function getProgramInfo() {
        $(".begin-edit").click(function () {
            var program_id = $(this).attr('id');
            console.log("Edit clicked");
            getAllRunlists('#editProgramModal');   // Populates the modal
            getAllPrograms('#editProgramModal');
            $.post('get-program/' + program_id, null, function (response) {
                var program = JSON.parse(response['program']);
                var runlist = JSON.parse(response['runlist']);
                console.log(runlist);
                var edit_modal = $('#editProgramModal');    // Display all of the current data for the program selected
                edit_modal.find('#name').val(program['pname']);
                edit_modal.find('#path').val(program['path']);
                edit_modal.find('#memUsage').val(program['estimated_memory_usage']);
                edit_modal.find('#dependencies').val("TODO");
                // edit_modal.find('#runlists');
                edit_modal.find('#args').val(program['command_line']);
                edit_modal.find('#pid').val(program_id);
                edit_modal.modal('show');
            });
        });
    }

    function getAllPrograms(modal_id){  // Get all program names. Used mainly for dependency selection.
            $.post('get-program-list', null, function(response){
                var modal = $(modal_id);
                response['programs'].forEach(function (element) {
                    var new_option = '<option value=' + element.pid + '>' + element.pname + '</option>';
                    console.log(new_option);
                    modal.find('#dependencies').append(new_option);
                });

            });
    }

    function handleRunlist(){
        // Handles modals for adding or editing runlists
        $(".runlist-modal-submit").click(function(){

            var form_id = $(this).attr('id');
            var data = $('form[id=' + form_id + ']').serializeArray();
            console.log(data);
            $.post(form_id, data, function (response) { // This will handle both creating a new program and updating an old one
                console.log(response);
            }, 'json');
        });
    }

    function deleteProgram() {
        $('.delete-program').click(function () {
            var data = $('form[id="edit-program"]').serializeArray();
            console.log(data);
            $.post('delete-program', data , function(response){
               console.log(response);
          });
        });

    }

    function deleteRunlist() {
        $('.delete-runlist').click(function () {
            var data = $('form[id="edit-runlist"]').serializeArray();
            console.log(data);
            $.post('delete-runlist', data , function(response){
                console.log(response);
            });
        });

    }

    function getAllRunlists(modal_id){
        // Gets all the runlists, for adding them to the select box
        $.post('get-runlist-list', null, function(response){
            var modal = $(modal_id);
            modal.find('#runlists').append('<option value=-1></option>');
            response['runlists'].forEach(function (element) {
                console.log(element);
                var new_option = '<option value=' + element.rpid + '>' + element.rname + '</option>';
                modal.find('#runlists').append(new_option);
            });
        });
    }

    function getRunlistInfo(){
        $(".begin-edit-runlist").click(function () {
            var runlist_id = $(this).attr('id');
            console.log("Edit Runlist clicked " + runlist_id);
            var edit_modal = $('#editRunlistModal');    // Display all of the current data for the program selected
            $.post('get-runlist/' + runlist_id, null, function (response) {
                console.log(response);
                var runlist = response['runlist'];
                console.log(runlist);
                edit_modal.find('#name').val(runlist['rname']);
                edit_modal.find('#time').val(runlist['rtime']);
                edit_modal.find('#rpid').val(runlist_id);
                edit_modal.modal('show');
            });
        });
    }

    getAllRunlists('#addProgramModal');
    getAllPrograms('#addProgramModal');

    getRunlistInfo();
    deleteRunlist();
    handleRunlist();
    getProgramInfo();
    handleProgram();
    deleteProgram();

});