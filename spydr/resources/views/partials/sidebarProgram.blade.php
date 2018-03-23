<div class="panel-group individual-program">
    <div class="panel panel-default">
        <div class="panel-heading">
            <h4 class="panel-title">
                <a href="#program-collapse-{{$program['program_id']}}" data-toggle="collapse">{{ $program['program_name'] }}</a>
            </h4>
        </div>
    </div>
</div>

<div id="program-collapse-{{$program['program_id']}}" class="panel-collapse collapse">
    <ul class="list-group">
        <li class="list-group-item">Memory: {{$program['program_memory']}}</li>
        <li class="list-group-item">CPU Time: {{$program['program_cpu_time']}}</li>
        <li class="list-group-item">Path: {{$program['program_path']}}</li>
        <li class="list-group-item">Edit {{--Javascript call here--}}</li>
    </ul>
</div>
<br>