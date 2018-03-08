@extends('layouts.master')

@section('title', 'Home')

@section('content')
    @include('partials.topbar')
    <div class="container">
        <div class="col-md-3">
            @include('partials.sidebar')
        </div>
        <div class="col-md-9">
            Hi
        </div>
    </div>
@endsection