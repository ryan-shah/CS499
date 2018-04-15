{{-- This is the form used for the popup that appears when 'Add Runlist' is clicked --}}

<div class="modal fade" id="addRunlistModal" role="dialog" aria-labelledby="addRunlistModalLabel">
    <div class="modal-dialog" role="document">
        <div class="modal-content">
            <div class="modal-header">
                <h4 class="modal-title" id="addRunlistModalLabel">Add Runlist</h4>
            </div>
            <div class="modal-body">
                <form class="form-group-row" id="add-runlist">
                    <label for="name">Name:</label>
                    <input type="text" class="form-control" id="name" name="name">
                    {{-- For now, the runlist will run every day. -Alijah --}}
                    <br>
                    <label for="time">Time:</label>
                    <input type="time" class="form-control" value="20:00" id="time" name="time">

                </form>
            </div>
            <div class="modal-footer">
                <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
                <button type="button" class="btn btn-primary runlist-modal-submit" id="add-runlist" data-dismiss="modal">Save changes</button>
            </div>
        </div>
    </div>
</div>