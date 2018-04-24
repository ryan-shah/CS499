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
        "KB" => 10**3,
        "MB" => 10**6,
        "GB" => 10**9
    );
    // Repetitive code, sure, but I doubt we'll need to change it much in the future anyway...
    if($bytes >= $memory["GB"]){
        return (string)(round($bytes/$memory["GB"], 2)) . "GB";
    }

    if($bytes >= $memory["MB"]){
        return (string)(round($bytes/$memory["MB"], 2)) . "MB";
    }

    if($bytes >= $memory["KB"]){
        return (string)(round($bytes/$memory["KB"], 2)) . "KB";
    }

    return (string)$bytes . "B";

}

/**
 * @param $string    Days run as an unformatted string
 * @return $string   Days run as a formatted string
 */
function format_days($string) {

    $string = str_replace('[', '', $string);
    $string = str_replace(']', '', $string);
    $string = str_replace('"', '', $string);
    $string = str_replace(',', ', ', $string);
    return $string;

}