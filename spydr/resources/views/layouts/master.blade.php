<!doctype html>
<html>

    <head>
        <link href="{{ asset('css/darkly.css') }}" rel="stylesheet">
        <link href="{{ asset('css/style.css') }}" rel="stylesheet">
        <link href="{{ asset('js/app.css') }}" rel="stylesheet">

        <meta name="viewport" content="width=device-width, initial-scale=1">

        <title> @yield('title')</title>
    </head>

    <body>
        <div class="container-fluid">
            @include('partials.topbar')
            <div class="row">
                @yield('content')
            </div>
        </div>
    </body>



</html>