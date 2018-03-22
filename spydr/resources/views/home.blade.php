@extends('layouts.master')

@section('title', 'Home')

@include('partials.topbar')

@section('content')
    <div class="col-sm-2">
        @include('partials.sidebar')
    </div>
    <div class="col-sm-10">
        <div class="flex-container">
            <div class="statistics">
                Statistics
            </div>

            <div class="run-list">
                <button type="button" class="btn btn-outline-success btn-sm add-runlist-button" data-toggle="modal" data-target="#addRunlistModal">
                    Add Runlist {{-- Launch "Add Runlist" modal --}}
                </button>
                Placeholder Runlist 1: {{-- Add these for each entry --}}
                <button type="button" class="btn btn-outline-success btn-sm edit-runlist-button" data-toggle="modal" data-target="#editRunlistModal">
                    Edit Placeholder Runlist 1 {{-- Launch "Edit Runlist" modal, and have the button name the associated runlist --}}
                </button>
                Placeholder Runlist 2: {{-- Add these for each entry --}}
                <button type="button" class="btn btn-outline-success btn-sm edit-runlist-button" data-toggle="modal" data-target="#editRunlistModal">
                    Edit Placeholder Runlist 2 {{-- Launch "Edit Runlist" modal, and have the button name the associated runlist --}}
                </button>
                Placeholder Runlist 3: {{-- Add these for each entry --}}
                <button type="button" class="btn btn-outline-success btn-sm edit-runlist-button" data-toggle="modal" data-target="#editRunlistModal">
                    Edit Placeholder Runlist 3 {{-- Launch "Edit Runlist" modal, and have the button name the associated runlist --}}
                </button>
                Placeholder Runlist 4: {{-- Add these for each entry --}}
                <button type="button" class="btn btn-outline-success btn-sm edit-runlist-button" data-toggle="modal" data-target="#editRunlistModal">
                    Edit Placeholder Runlist 4 {{-- Launch "Edit Runlist" modal, and have the button name the associated runlist --}}
                </button>
            </div>
        </div>
    </div>
@endsection