{{-- This displays the information regarding each program in the database --}}

<div class="panel-group individual-program">
    <div class="panel panel-default">
        <div class="panel-heading">
            <h4 class="panel-title">
                <a href="#program-collapse-{{$program->pid}}" data-toggle="collapse">{{ $program->pname }}</a>
            </h4>
        </div>
    </div>
</div>

<div id="program-collapse-{{$program->pid}}" class="panel-collapse collapse">
    <ul class="list-group">
        <li class="list-group-item">Memory: {{format_memory($program->estimated_memory_usage)}}</li>
        <li class="list-group-item">CPU Time: {{format_time($program->estimated_time)}}</li>
        <li class="list-group-item">Path: {{$program->path}}</li>
        <li class="list-group-item">Arguments: {{$program->command_line}}</li>
        <li class="list-group-item begin-edit" id="{{$program->pid}}" style="text-align: center;"><a href="#">Edit</a></li>
    </ul>
</div>
<br>