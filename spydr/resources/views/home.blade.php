@extends('layouts.master')

@section('title', 'Home')

@include('partials.topbar')

@section('content')
    <div class="col-sm-2">
        @include('partials.sidebar')
    </div>
    <div class="col-sm-10">
        <div class="flex-container">
            @include('partials.statistics')

            <div class="run-list">
            @include('partials.runlists')
            </div>
        </div>
    </div>
@endsection