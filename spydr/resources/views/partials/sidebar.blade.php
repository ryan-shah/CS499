<div class="sidebar">
    <form class="form-group-row">
        <input class="form-control search-program" type="text" placeholder="Search">
        <button class="btn btn-outline-success btn-sm" type="submit">Go</button>
    </form>

    <button type="button" class="btn btn-outline-success btn-sm add-program-button" data-toggle="modal" data-target="#addProgramModal">
        Add Program {{-- Launch "Add Progam" modal --}}
    </button>

    @each('partials.sidebarProgram', $programs, 'program')

</div>