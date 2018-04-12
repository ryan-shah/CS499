{{-- This page presents the 'Add Runlist' button and a list of runlists with their respective 'Edit Runlists' buttons --}}

<button type="button" class="btn btn-outline-success btn-sm add-runlist-button" data-toggle="modal" data-target="#addRunlistModal">
    Add Runlist {{-- Launch "Add Runlist" modal --}}
</button>

@each('partials.runlistProgram', $runlist_parameters, 'runlist_parameter')