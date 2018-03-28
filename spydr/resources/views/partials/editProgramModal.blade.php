<div class="modal fade" id="editProgramModal" role="dialog" aria-labelledby="editProgramModalLabel">
    <div class="modal-dialog" role="document">
        <div class="modal-content">
            <div class="modal-header">
                <h4 class="modal-title" id="editProgramModalLabel">Add Program</h4>
            </div>
            <div class="modal-body">
                <form class="form-group-row">
                    <label for="name">Name:</label>
                    <input type="name" class="form-control" id="name">
                </form>
                <form class="form-group-row">
                    <label for="path">Absolute Path:</label>
                    <input type="path" class="form-control" id="path">
                </form>
                <form class="form-group-row">
                    <label for="memUsage">Expected Memory Usage:</label>
                    <input type="memUsage" class="form-control" id="memUsage">
                </form>
                <form class="form-group-row">
                    <label for="dependencies">Dependencies:</label>
                    <input type="dependencies" class="form-control" id="dependencies">
                </form>
                <form class="form-group-row">
                    <label for="runlist">Runlist:</label>
                    <input type="runlist" class="form-control" id="runlist">
                </form>
            </div>
            <div class="modal-footer">
                <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
                <button type="button" class="btn btn-primary" onclick="editProgram()" data-dismiss="modal">Save changes</button>
            </div>
        </div>
    </div>
</div>