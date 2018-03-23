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
                @include('partials.statistics')
            </div>

            <div class="run-list">

            </div>
        </div>
    </div>
@endsection