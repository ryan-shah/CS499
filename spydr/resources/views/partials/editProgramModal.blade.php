{{-- This is the form used for the popup that appears when 'Edit Program' is clicked [NOT FULLY IMPLEMENTED] --}}

<div class="modal fade" id="editProgramModal" role="dialog" aria-labelledby="editProgramModalLabel">
    <div class="modal-dialog" role="document">
        <div class="modal-content">
            <div class="modal-header">
                <h4 class="modal-title" id="editProgramModalLabel">Edit Program</h4>
            </div>
            <div class="modal-body">
                <form class="form-group-row edit-program-form" id="edit-program">
                    <label for="name">Name:</label>
                    <input type="text" class="form-control" id="name" name="name">
                    <br>
                    <label for="path">Absolute Path:</label>
                    <input type="text" class="form-control" id="path" name="path">
                    <br>
                    <label for="memUsage">Expected Memory Usage:</label>
                    <input type="text" class="form-control" id="memUsage" name="memUsage">
                    <br>
                    <label for="dependencies">Dependencies:</label>
                    <input type="text" class="form-control" id="dependencies" name="dependencies">
                    <br>
                    <label for="runlists">Runlist:</label>
                    <select class="form-control" id="runlists" name="runlists">
                        {{-- Populated by an AJAX post request --}}
                    </select>
                    <br>
                    <label for="args">Additional Arguments:</label>
                    <input type="text" class="form-control" id="args" name="args">

                    <input type="hidden" id="pid" value="" name="pid">
                </form>
            </div>
            <div class="modal-footer">
                <button type="button" class="btn btn-danger delete-program" id="delete-program" data-dismiss="modal">Delete Program</button>
                <div class="button-spacer"></div>
                <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
                {{--<button type="button" class="btn btn-primary program-modal-submit" id="edit-program" data-dismiss="modal">Save changes</button> - NOT IMPLEMENTED--}}
            </div>
        </div>
    </div>
</div>