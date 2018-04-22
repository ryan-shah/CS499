{{-- This page presents a search bar for the programs with its repective button, an 'Add Program' button, and a list of programs with their respective 'Edit Program' buttons --}}
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