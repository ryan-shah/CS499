{{-- This page presents an 'Add Program' button and a list of programs with their respective 'Edit Program' buttons --}}

<div class="sidebar">

    <button type="button" class="btn btn-outline-success btn-sm add-program-button" data-toggle="modal" data-target="#addProgramModal">
        Add Program {{-- Launch "Add Progam" modal --}}
    </button>

    <br>

    @each('partials.sidebarProgram', $programs, 'program')

</div>