<!doctype html>
<html>

    <head>
        <link href="{{ asset('css/darkly.css') }}" rel="stylesheet">
        <link href="{{ asset('css/style.css') }}" rel="stylesheet">
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script>
        <script src="{{ asset('js/app.js') }}"></script>
        <script src="{{ asset('js/spydr.js') }}"></script>

        <meta name="viewport" content="width=device-width, initial-scale=1">
        <meta name="csrf-token" content="{{ csrf_token() }}">

        <title> @yield('title')</title>
    </head>

    <body>
        <div class="container-fluid">
            {{--@include('partials.topbar') --}}{{-- We probably don't want the navbar on every page --}}
            <div class="row">
                @yield('content')
            </div>
        </div>
    </body>

    @include('layouts.modals')

</html>