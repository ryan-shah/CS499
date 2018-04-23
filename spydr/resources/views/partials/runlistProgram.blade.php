{{-- This displays the information regarding each runlist in the database --}}

<div class="panel-group individual-runlist">
    <div class="panel panel-default">
        <div class="panel-heading">
            <h4 class="panel-title">
                <a href="#runlist-collapse-{{$runlist_parameter->rpid}}" data-toggle="collapse">{{ $runlist_parameter->rname }}</a>
            </h4>
        </div>
    </div>
</div>

<div id="runlist-collapse-{{$runlist_parameter->rpid}}" class="panel-collapse collapse">
    <ul class="list-group">
        <li class="list-group-item"> {{-- Memory: {{format_memory($runlist_parameter->estimated_memory_usage)}} --}} Placeholder Statistics</li>
         {{-- i'll take out the inline style later... -Alijah --}}
        <li class="list-group-item begin-edit-runlist" id="{{$runlist_parameter->rpid}}" style="text-align: center;"><a href="#">Edit</a></li>
    </ul>
</div>
<br>