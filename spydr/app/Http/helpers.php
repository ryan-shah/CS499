<?php
/**
 * Created by PhpStorm.
 * User: Alijah
 * Date: 3/26/2018
 * Time: 12:51 PM
 */

/**
 * @param integer $seconds  Amount of time in seconds
 * @return string           The time in the format 00h00m00s
 * **/
function format_time($seconds) {
    $minutes = floor($seconds / 60);
    $hours = floor($minutes / 60);

    // Now we want to pad the values so that they always match the return value format
    $padded_hours = sprintf("%02dh", $hours);
    $padded_minutes = sprintf("%02dm", $minutes % 60);
    $padded_seconds = sprintf("%02ds", $seconds % 60);

    $total_time = $padded_hours . $padded_minutes . $padded_seconds;

    return $total_time;
}

/**
 * @param $bytes    Amount of memory in bytes
 * @return string   Amount of memory given in B, KB, MB, or GB.
 */
function format_memory($bytes) {
    $memory = array (
        // This is only for display, so memory will be calculated in powers of 10
        "B" => 10**0,
        "KB" => 10**3,
        "MB" => 10**6,
        "GB" => 10**9
    );
    // Repetitive code, sure, but I doubt we'll need to change it much in the future anyway...
    if($bytes >= $memory["GB"]){
        return (string)($bytes/$memory["GB"]) . "GB";
    }

    if($bytes >= $memory["MB"]){
        return (string)($bytes/$memory["MB"]) . "MB";
    }

    if($bytes >= $memory["KB"]){
        return (string)($bytes/$memory["KB"]) . "KB";
    }

    return (string)$bytes . "B";

}