<div class="panel-group individual-program">
    <div class="panel panel-default">
        <div class="panel-heading">
            <h4 class="panel-title">
                <a href="#program-collapse-{{$program->id}}" data-toggle="collapse">{{ $program->name }}</a>
            </h4>
        </div>
    </div>
</div>

<div id="program-collapse-{{$program->id}}" class="panel-collapse collapse">
    <ul class="list-group">
        <li class="list-group-item">Memory: {{format_memory($program->estimated_memory_usage)}}</li>
        <li class="list-group-item">CPU Time: {{format_time($program->estimated_time)}}</li>
        <li class="list-group-item">Path: {{$program->path}}</li>
        {{-- i'll take out the inline style later... -Alijah --}}
        <li class="list-group-item" style="text-align: center;"><a href="#" onclick="editProgram({{$program->id}})">Edit</a></li>
    </ul>
</div>
<br>