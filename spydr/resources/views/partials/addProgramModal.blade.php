<div class="modal fade" id="addProgramModal" role="dialog" aria-labelledby="addProgramModalLabel">
    <div class="modal-dialog" role="document">
        <div class="modal-content">
            <div class="modal-header">
                <h4 class="modal-title" id="addProgramModalLabel">Add Program</h4>
            </div>
            <div class="modal-body">
                <form class="form-group-row add-program-form" id="add-program">
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
                    <select multiple class="form-control" id="dependencies", name="dependencies">
                        {{-- This gets populated by an AJAX post request --}}
                    </select>
                    <br>
                    <label for="runlist">Runlist:</label>
                    <input type="text" class="form-control" id="runlist" name="runlist">
                    <br>
                    <label for="args">Additional Arguments:</label>
                    <input type="text" class="form-control" id="args" name="args">
                </form>
            </div>
            <div class="modal-footer">
                <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
                <button type="button" class="btn btn-primary modal-submit" id="add-program" data-dismiss="modal">Save changes</button>
            </div>
        </div>
    </div>
</div>