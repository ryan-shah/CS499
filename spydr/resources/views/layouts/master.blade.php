<!doctype html>
<html>

    <head>
        <link href="{{ asset('css/darkly.css') }}" rel="stylesheet">
        <link href="{{ asset('css/style.css') }}" rel="stylesheet">
        <script src="{{ asset('js/app.js') }}"></script>
        <script src="{{ asset('js/spydr.js') }}"></script>

        <meta name="viewport" content="width=device-width, initial-scale=1">

        <title> @yield('title')</title>
    </head>

    <body>
        <div class="container-fluid">
            @include('partials.topbar') {{-- We probably want the navbar on every page --}}
            <div class="row">
                @yield('content')
            </div>
        </div>
    </body>

    @include('layouts.modals')

</html>