{{-- This code is calls on master.blade.php and some files in the partials directory to create the homepage --}}

@extends('layouts.master')

@section('title', 'Home')

@include('partials.topbar')

{{-- This controls how wide the sidebar and other content are [TO HAVE CODE UNCOMMENTED ONCE STATISTICS ARE IMPLEMENTED] --}}
@section('content')
    <div class="col-sm-6">
        @include('partials.sidebar')
    </div>
    <div class="col-sm-6">
        {{--<div class="flex-container">--}}
            {{--@include('partials.statistics')--}}

            <div class="run-list">
                @include('partials.runlists')
            </div>
        {{--</div>--}}
    </div>
@endsection