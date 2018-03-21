@extends('layouts.master')

@section('title', 'Login')

@include('partials.topbarLogin')

@section('content')
    <div class="login-container">
        <form>
            <p>Username: </p><input class="form-control" type="text" placeholder="Username">
            <p>Password: </p><input class="form-control" type="password" placeholder="Password">
            <button class="btn btn-outline-success submit" type="submit">Login</button>
        </form>
    </div>
@endsection