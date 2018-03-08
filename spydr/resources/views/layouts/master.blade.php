<!doctype html>
<html>

    <head>
        <link href="{{ asset('css/darkly.css') }}" rel="stylesheet">
        <link href="{{ asset('css/style.css') }}" rel="stylesheet">
        <link href="{{ asset('js/app.css') }}" rel="stylesheet">

        <title> @yield('title')</title>
    </head>

    <body>
        <div class="container-fluid">
            @yield('content')
        </div>
    </body>



</html>