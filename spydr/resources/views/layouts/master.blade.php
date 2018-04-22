{{-- This file contains a general layout that the webpages follow --}}

<!doctype html>
<html>

    {{-- Call each of the necessary stylesheets and JS files --}}
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

    {{-- This calls the 'content' in home.blade.php --}}
    <body>
        <div class="container-fluid">
            <div class="row">
                @yield('content')
            </div>
        </div>
    </body>

    @include('layouts.modals')

</html>