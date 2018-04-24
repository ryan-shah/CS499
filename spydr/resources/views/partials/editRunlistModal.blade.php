{{-- This is the form used for the popup that appears when 'Edit Runlist' is clicked [NOT FULLY IMPLEMENTED] --}}

<div class="modal fade" id="editRunlistModal" role="dialog" aria-labelledby="editRunlistModalLabel">
    <div class="modal-dialog" role="document">
        <div class="modal-content">
            <div class="modal-header">
                <h4 class="modal-title" id="editRunlistModalLabel">Edit Runlist</h4>
            </div>
            <div class="modal-body">
                <form class="form-group-row" id="edit-runlist">
                    <label for="name">Name:</label>
                    <input type="text" class="form-control" id="name" name="name">
                    {{-- For now, the runlist will run every day. -Alijah --}}
                    <br>
                    <label for="time">Time:</label>
                    <input type="time" class="form-control" value="20:00" id="time" name="time">
                    <input type="hidden" class="rpid" id="rpid" name="rpid">
                </form>
            </div>
            <div class="modal-footer">
                <button type="button" class="btn btn-danger delete-runlist" id="delete-runlist" data-dismiss="modal">Delete Runlist</button>
                <div class="button-spacer"></div>
                <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
                <button type="button" class="btn btn-primary runlist-modal-submit" id="add-runlist" data-dismiss="modal">Save changes</button>
            </div>
        </div>
    </div>
</div>